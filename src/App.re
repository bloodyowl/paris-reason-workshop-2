include CssReset;

type state = {
  url: ReasonReact.Router.url,
  beerList: RequestStatus.t(Belt.Result.t(array(BeerList.t), Errors.t)),
  beers:
    Belt.Map.String.t(
      RequestStatus.t(Belt.Result.t((float, BeerDetail.t), Errors.t)),
    ),
};

type action =
  | SetUrl(ReasonReact.Router.url)
  | LoadBeerList
  | ReceiveBeerList(Belt.Result.t(array(BeerList.t), Errors.t))
  | LoadBeerDetail(string)
  | ReceiveBeerDetail(string, Belt.Result.t(BeerDetail.t, Errors.t));

let component = ReasonReact.reducerComponent("App");

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
  initialState: () => {
    url: ReasonReact.Router.dangerouslyGetInitialUrl(),
    beerList: NotAsked,
    beers: Belt.Map.String.empty,
  },
  reducer: (action, state) => {
    switch (action) {
    | SetUrl(url) => ReasonReact.Update({...state, url})
    | LoadBeerList =>
      ReasonReact.UpdateWithSideEffects(
        {...state, beerList: Loading},
        ({send}) =>
          BeerList.query()
          ->Future.get(payload => send(ReceiveBeerList(payload))),
      )
    | ReceiveBeerList(beerList) =>
      ReasonReact.Update({...state, beerList: Done(beerList)})
    | LoadBeerDetail(id) =>
      ReasonReact.UpdateWithSideEffects(
        {...state, beers: state.beers->Belt.Map.String.set(id, Loading)},
        ({send}) =>
          BeerDetail.query(~id)
          ->Future.get(payload => send(ReceiveBeerDetail(id, payload))),
      )
    | ReceiveBeerDetail(id, payload) =>
      ReasonReact.Update({
        ...state,
        beers:
          state.beers
          ->Belt.Map.String.set(
              id,
              Done(payload->Belt.Result.map(ok => (Js.Date.now(), ok))),
            ),
      })
    };
  },
  didMount: ({send, onUnmount}) => {
    let watcherId = ReasonReact.Router.watchUrl(url => send(SetUrl(url)));
    onUnmount(() => ReasonReact.Router.unwatchUrl(watcherId));
  },
  render: ({state, send}) =>
    <>
      <Header />
      <div className=Styles.contents>
        {switch (state.url.path) {
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
         | _ => ReasonReact.string("Error: Route not found")
         }}
      </div>
      <Footer />
    </>,
};
