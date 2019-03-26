type t = {
  id: int,
  name: string,
  image_url: string,
  description: string,
};

let fromJs = jsBeer => {
  id: jsBeer##id,
  name: jsBeer##name,
  image_url: jsBeer##image_url,
  description: jsBeer##description,
};

let query = (~id) => {
  Request.make(~url=Environment.apiUrl ++ "/beers/" ++ id, ())
  ->Future.mapOk(item => fromJs(item[0]));
};
