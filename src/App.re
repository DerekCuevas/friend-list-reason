open Friend;

type friends = {
  count: int,
  query: string,
  results: list(friend),
};

let mockFriends = [
  {id: 0, name: "Derek", username: "DC"},
  {id: 1, name: "John", username: "JohnDoe"},
];

/* component */

type state = {
  query: string,
  friends: list(friend),
};

type action =
  | Search
  | SetQuery(string);

let initialState = () => {query: "", friends: mockFriends};

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
      <FriendList friends=self.state.friends />
    </div>,
};
