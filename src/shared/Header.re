[@bs.config {jsx: 3}];

module Styles = {
  open Css;
  let container =
    style([
      padding(20->px),
      backgroundColor(Theme.mainRed->hex),
      color("fff"->hex),
    ]);
  let text = style([textAlign(center), fontWeight(extraBold)]);
};

[@react.component]
let make = _ => {
  <header className=Styles.container>
    <a
      href="/"
      onClick={event => {
        event->ReactEvent.Mouse.preventDefault;
        ReasonReact.Router.push("/");
      }}>
      <div role="heading" ariaLevel=1 className=Styles.text>
        "ParisReason Workshop 2"->ReasonReact.string
      </div>
    </a>
  </header>;
};
