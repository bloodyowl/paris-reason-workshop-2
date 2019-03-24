include CssReset;

let component = ReasonReact.statelessComponent("App");

module Styles = {
  open Css;
  let contents =
    style([
      display(flexBox),
      flexDirection(column),
      alignItems(stretch),
      flexGrow(1.0),
    ]);
};

let make = _ => {
  ...component,
  render: _ =>
    <>
      <Header />
      <div className=Styles.contents>
        <h1> "Helloworld!"->ReasonReact.string </h1>
      </div>
      <Footer />
    </>,
};
