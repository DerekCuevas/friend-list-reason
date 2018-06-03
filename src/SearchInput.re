let component = ReasonReact.statelessComponent("SearchInput");

let make = (~value="", ~onInput, ~onEnter, _children) => {
  ...component,
  render: _self =>
    <input
      className="search-input"
      type_="search"
      placeholder="Search Friends"
      value
      onInput=(
        event =>
          onInput(
            ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value,
          )
      )
      onKeyDown=(
        event => {
          let keyCode = ReactEventRe.Keyboard.which(event);
          if (keyCode == 13) {
            onEnter();
          };
        }
      )
    />,
};
