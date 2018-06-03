type friend = {
  id: int,
  name: string,
  username: string,
};

type results = {
  count: int,
  friends: list(friend),
};

module Decode = {
  let friend = json =>
    Json.Decode.{
      id: json |> field("id", int),
      name: json |> field("name", string),
      username: json |> field("username", string),
    };

  let results = json =>
    Json.Decode.{
      count: json |> field("count", int),
      friends: json |> field("results", list(friend)),
    };
};
