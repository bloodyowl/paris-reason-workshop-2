type getFn('a) = ('a => unit) => unit;

type t('a) =
  | Future(getFn('a));

type status('a) =
  | Pending(list('a => unit))
  | Done('a);

let make: (('a => unit) => 'b) => t('a);

let value: 'a => t('a);

let map: (t('a), 'a => 'b) => t('b);

let flatMap: (t('a), 'a => t('b)) => t('b);

let tap: (t('a), 'a => unit) => t('a);

let get: (t('a), 'a => unit) => unit;

let mapOk:
  (t(Belt.Result.t('a, 'b)), 'a => 'c) => t(Belt.Result.t('c, 'b));

let mapError:
  (t(Belt.Result.t('a, 'b)), 'b => 'c) => t(Belt.Result.t('a, 'c));

let flatMapOk:
  (t(Belt.Result.t('a, 'b)), 'a => t(Belt.Result.t('c, 'b))) =>
  t(Belt.Result.t('c, 'b));

let flatMapError:
  (t(Belt.Result.t('a, 'b)), 'b => t(Belt.Result.t('a, 'c))) =>
  t(Belt.Result.t('a, 'c));

let tapOk:
  (t(Belt.Result.t('a, 'b)), 'a => 'c) => t(Belt.Result.t('a, 'b));

let tapError:
  (t(Belt.Result.t('a, 'b)), 'b => 'c) => t(Belt.Result.t('a, 'b));

let all2: ((t('a), t('b))) => t(('a, 'b));

let all3: ((t('a), t('b), t('c))) => t(('a, 'b, 'c));

let all4: ((t('a), t('b), t('c), t('d))) => t(('a, 'b, 'c, 'd));

let all5:
  ((t('a), t('b), t('c), t('d), t('e))) => t(('a, 'b, 'c, 'd, 'e));

let all6:
  ((t('a), t('b), t('c), t('d), t('e), t('f))) =>
  t(('a, 'b, 'c, 'd, 'e, 'f));

let all: Belt.List.t(t('a)) => t(Belt.List.t('a));

let mapAllOk:
  (t(Belt.List.t(Belt.Result.t('a, 'b))), Belt.List.t('a) => 'c) =>
  t(Belt.Result.t('c, Belt.Result.t('a, 'b)));

let flatMapAllOk:
  (t(Belt.List.t(Belt.Result.t('a, 'b))), 'c, Belt.List.t('a) => t('c)) =>
  t('c);

let toPromise: t('a) => Js.Promise.t('a);

external _toExn: 'a => exn = "%identity";

let toPromiseWithResult: t(Belt.Result.t('a, 'b)) => Js.Promise.t('a);
