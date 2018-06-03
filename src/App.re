open Friend;

let api = "http://localhost:8000/api/friends";

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
  | Search =>
    ReasonReact.UpdateWithSideEffects(
      {...state, results: Loading},
      (
        self =>
          Js.Promise.(
            Fetch.fetch(api ++ "?q=" ++ self.state.query)
            |> then_(Fetch.Response.json)
            |> then_(json =>
                 json
                 |> Decode.results
                 |> (results => self.send(SetResults(Success(results))))
                 |> resolve
               )
            |> catch(_err =>
                 Js.Promise.resolve(self.send(SetResults(Failure)))
               )
            |> ignore
          )
      ),
    )
  | SetQuery(query) =>
    ReasonReact.UpdateWithSideEffects(
      {...state, query},
      (self => self.send(Search)),
    )
  | SetResults(results) => ReasonReact.Update({...state, results})
  };

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState,
  reducer,
  didMount: self => self.send(Search),
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
        | Failure =>
          <Error
            message="Sorry! Request Failed. "
            details="Press enter to try again."
          />

        | Success(results) => <FriendList friends=results.friends />
        }
      )
    </div>,
};
