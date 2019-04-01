open Belt;

type update('action, 'state) =
  | NoUpdate
  | Update('state)
  | UpdateWithSideEffects('state, self('action, 'state) => unit)
  | SideEffects(self('action, 'state) => unit)
and self('action, 'state) = {
  send: 'action => unit,
  state: 'state,
}
and fullState('action, 'state) = {
  state: 'state,
  sideEffects: ref(array(self('action, 'state) => unit)),
};

let useReducer = (initialState, reducer) => {
  let ({state, sideEffects}, setState) =
    React.useState(() => {state: initialState, sideEffects: ref([||])});
  let send = action =>
    switch (reducer(action, state)) {
    | NoUpdate => ()
    | Update(state) => setState(fullState => {...fullState, state})
    | UpdateWithSideEffects(state, sideEffect) =>
      setState(({sideEffects}) =>
        {
          state,
          sideEffects: ref(Array.concat(sideEffects^, [|sideEffect|])),
        }
      )
    | SideEffects(sideEffect) =>
      setState(fullState =>
        {
          ...fullState,
          sideEffects:
            ref(Array.concat(fullState.sideEffects^, [|sideEffect|])),
        }
      )
    };
  React.useEffect1(
    () => {
      if (Array.length(sideEffects^) > 0) {
        Array.forEach(sideEffects^, func => func({state, send}));
        sideEffects := [||];
      };
      None;
    },
    [|sideEffects^|],
  );
  (state, send);
};
