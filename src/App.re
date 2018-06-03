open Friend;

let api = "https://localhost:8000/api/friends";

type results = {
  count: int,
  query: string,
  friends: list(friend),
};

type webData('a) =
  | NotAsked
  | Loading
  | Success('a)
  | Failure;

type state = {
  query: string,
  results: webData(results),
};

type action =
  | Search
  | SetQuery(string)
  | SetResults(webData(results));

let initialState = () => {query: "", results: NotAsked};

let reducer = (action, state) =>
  switch (action) {
  | Search => ReasonReact.NoUpdate
  | SetQuery(query) => ReasonReact.Update({...state, query})
  | SetResults(results) => ReasonReact.Update({...state, results})
  };

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState,
  reducer,
  render: self =>
    <div className="app">
      <SearchInput
        value=self.state.query
        onInput=(query => self.send(SetQuery(query)))
        onEnter=(_ => self.send(Search))
      />
      (
        switch (self.state.results) {
        | NotAsked => <p> (ReasonReact.string("Not Asked")) </p>
        | Loading => <p> (ReasonReact.string("Loading...")) </p>
        | Failure => <p> (ReasonReact.string("Failed!!")) </p>
        | Success(results) => <FriendList friends=results.friends />
        }
      )
    </div>,
};
