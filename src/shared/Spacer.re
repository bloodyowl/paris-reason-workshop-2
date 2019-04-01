[@bs.config {jsx: 3}];

[@react.component]
let make = (~width as widthPx=10, ~height as heightPx=10, _) => {
  <div
    className=Css.(
      style([width(widthPx->px), height(heightPx->px), flexShrink(0)])
    )
  />;
};
