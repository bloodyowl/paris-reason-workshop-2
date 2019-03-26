type t = {
  id: int,
  name: string,
  image_url: string,
};

let fromJs = jsBeer => {
  id: jsBeer##id,
  name: jsBeer##name,
  image_url: jsBeer##image_url,
};

let query = () => {
  Request.make(~url=Environment.apiUrl ++ "/beers", ())
  ->Future.mapOk(items => items->Belt.Array.map(fromJs));
};
