let component = ReasonReact.statelessComponent("Footer");

module Styles = {
  open Css;
  let container =
    style([
      padding(10->px),
      backgroundColor(Theme.darkBody->hex),
      color("fff"->hex),
    ]);
  let text = style([textAlign(center)]);
};

let make = _ => {
  ...component,
  render: _ =>
    <header className=Styles.container>
      <div className=Styles.text>
        {j|© 2019 - ParisReason|j}->ReasonReact.string
      </div>
    </header>,
};
