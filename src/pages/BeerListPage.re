let component = ReasonReact.statelessComponent("BeerListPage");

module Styles = {
  open Css;
  let item =
    style([
      padding(10->px),
      borderBottomWidth(1->px),
      borderBottomStyle(solid),
      borderBottomColor(rgba(0, 0, 0, 0.1)),
      display(flexBox),
      flexDirection(row),
      alignItems(center),
    ]);
  let text = style([marginLeft(20->px)]);
};
let make =
    (
      ~beerList: RequestStatus.t(Belt.Result.t(array(BeerList.t), Errors.t)),
      ~onLoadRequest,
      _,
    ) => {
  ...component,
  didMount: _ => {
    switch (beerList) {
    | NotAsked => onLoadRequest()
    | _ => ()
    };
  },
  render: _ =>
    <div>
      {switch (beerList) {
       | NotAsked => ReasonReact.null
       | Loading => ReasonReact.string("Loading")
       | Done(Error(_)) => ReasonReact.string("Request failed")
       | Done(Ok(beers)) =>
         beers
         ->Belt.Array.map(beer =>
             <a
               href={"/beers/" ++ string_of_int(beer.id)}
               onClick={event => {
                 event->ReactEvent.Mouse.preventDefault;
                 ReasonReact.Router.push(
                   "/beers/" ++ string_of_int(beer.id),
                 );
               }}
               className=Styles.item
               key={beer.id->string_of_int}>
               <img src={beer.image_url} width="32" alt="" />
               <div className=Styles.text> beer.name->ReasonReact.string </div>
             </a>
           )
         ->ReasonReact.array
       }}
    </div>,
};
