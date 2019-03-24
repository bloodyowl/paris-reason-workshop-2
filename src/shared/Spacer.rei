let make:
  (~width: int=?, ~height: int=?, array(ReasonReact.reactElement)) =>
  ReasonReact.component(
    ReasonReact.stateless,
    ReasonReact.noRetainedProps,
    ReasonReact.actionless,
  );
