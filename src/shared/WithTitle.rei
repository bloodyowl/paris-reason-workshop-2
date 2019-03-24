type state;

type action;

let make:
  (~title: string, array(ReasonReact.reactElement)) =>
  ReasonReact.component(state, ReasonReact.noRetainedProps, action);
