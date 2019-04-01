[@bs.config {jsx: 3}];

include CssReset;

type state = {
  beerList: RequestStatus.t(Belt.Result.t(array(BeerList.t), Errors.t)),
  beers:
    Belt.Map.String.t(
      RequestStatus.t(Belt.Result.t((float, BeerDetail.t), Errors.t)),
    ),
};

type action =
  | LoadBeerList
  | ReceiveBeerList(Belt.Result.t(array(BeerList.t), Errors.t))
  | LoadBeerDetail(string)
  | ReceiveBeerDetail(string, Belt.Result.t(BeerDetail.t, Errors.t));

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

[@react.component]
let make = _ => {
  let (state, send) =
    ReactUpdate.useReducer(
      {beerList: NotAsked, beers: Belt.Map.String.empty}, (action, state) =>
      switch (action) {
      | LoadBeerList =>
        UpdateWithSideEffects(
          {...state, beerList: Loading},
          ({send}) =>
            BeerList.query()
            ->Future.get(payload => send(ReceiveBeerList(payload))),
        )
      | ReceiveBeerList(beerList) =>
        Update({...state, beerList: Done(beerList)})
      | LoadBeerDetail(id) =>
        UpdateWithSideEffects(
          {...state, beers: state.beers->Belt.Map.String.set(id, Loading)},
          ({send}) =>
            BeerDetail.query(~id)
            ->Future.get(payload => send(ReceiveBeerDetail(id, payload))),
        )
      | ReceiveBeerDetail(id, payload) =>
        Update({
          ...state,
          beers:
            state.beers
            ->Belt.Map.String.set(
                id,
                Done(payload->Belt.Result.map(ok => (Js.Date.now(), ok))),
              ),
        })
      }
    );
  let url = ReasonReactRouter.useUrl();
  <>
    <Header />
    <div className=Styles.contents>
      {switch (url.path) {
       | [] =>
         <BeerListPage
           onLoadRequest={() => send(LoadBeerList)}
           beerList={state.beerList}
         />
       | ["beers", id] =>
         <BeerDetailPage
           onLoadRequest={() => {
             Js.log("load beer detail");
             send(LoadBeerDetail(id));
           }}
           beer={
             state.beers
             ->Belt.Map.String.get(id)
             ->Belt.Option.getWithDefault(NotAsked)
           }
         />
       | _ => React.string("Error: Route not found")
       }}
    </div>
    <Footer />
  </>;
};
