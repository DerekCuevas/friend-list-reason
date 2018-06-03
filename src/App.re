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
  | NoOp;

let initialState = () => {query: "", friends: mockFriends};

let reducer = (action, _state) =>
  switch (action) {
  | NoOp => ReasonReact.NoUpdate
  };

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState,
  reducer,
  render: self =>
    <div className="app">
      <SearchInput />
      <FriendList friends=self.state.friends />
    </div>,
};
