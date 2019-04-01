[@bs.config {jsx: 3}];

[@react.component]
let make =
    (
      ~beer: RequestStatus.t(Belt.Result.t((float, BeerDetail.t), Errors.t)),
      ~onLoadRequest,
      _,
    ) => {
  React.useEffect0(() => {
    {
      switch (beer) {
      | NotAsked => onLoadRequest()
      | Done(Ok((lastDate, _))) when Js.Date.now() -. lastDate > 10_000. =>
        onLoadRequest()
      | _ => ()
      };
    };
    None;
  });
  <div>
    {switch (beer) {
     | NotAsked => React.null
     | Loading => React.string("Loading")
     | Done(Error(_)) => React.string("Beer not found")
     | Done(Ok((_, beer))) =>
       <div>
         <img src={beer.image_url} alt="" />
         <h1> beer.name->React.string </h1>
         <p> beer.description->React.string </p>
       </div>
     }}
  </div>;
};
