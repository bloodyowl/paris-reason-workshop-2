[@bs.config {jsx: 3}];

let suffix = title =>
  title == "Putain de code" ? title : title ++ " | Putain de code";

[@react.component]
let make = (~title, ~children) => {
  React.useEffect1(
    () => {
      Seo.set(~title=title->suffix, ());
      None;
    },
    [|title|],
  );
  children;
};
