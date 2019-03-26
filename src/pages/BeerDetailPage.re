let component = ReasonReact.statelessComponent("BeerDetalPage");

let make =
    (
      ~beer: RequestStatus.t(Belt.Result.t((float, BeerDetail.t), Errors.t)),
      ~onLoadRequest,
      _,
    ) => {
  ...component,
  didMount: _ => {
    switch (beer) {
    | NotAsked => onLoadRequest()
    | Done(Ok((lastDate, _))) when Js.Date.now() -. lastDate > 10_000. =>
      onLoadRequest()
    | _ => ()
    };
  },
  render: _ =>
    <div>
      {switch (beer) {
       | NotAsked => ReasonReact.null
       | Loading => ReasonReact.string("Loading")
       | Done(Error(_)) => ReasonReact.string("Beer not found")
       | Done(Ok((_, beer))) =>
         <div>
           <img src={beer.image_url} alt="" />
           <h1> beer.name->ReasonReact.string </h1>
           <p> beer.description->ReasonReact.string </p>
         </div>
       }}
    </div>,
};
