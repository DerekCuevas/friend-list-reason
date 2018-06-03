let component = ReasonReact.statelessComponent("SearchInput");

let make = _children => {
  ...component,
  render: _self => <div> (ReasonReact.string("SearchInput")) </div>,
};
