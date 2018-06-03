open Friend;

type results = {
  count: int,
  query: string,
  friends: list(friend),
};

let mockResults = {
  count: 2,
  query: "q",
  friends: [
    {id: 0, name: "Derek", username: "DC"},
    {id: 1, name: "John", username: "JohnDoe"},
  ],
};

/* component */

type state = {
  query: string,
  results,
};

type action =
  | Search
  | SetQuery(string);

let initialState = () => {query: "", results: mockResults};

let reducer = (action, state) =>
  switch (action) {
  | Search => ReasonReact.NoUpdate
  | SetQuery(query) => ReasonReact.Update({...state, query})
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
      />
      <FriendList friends=self.state.results.friends />
    </div>,
};
