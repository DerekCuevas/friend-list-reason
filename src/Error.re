let component = ReasonReact.statelessComponent("Error");

let make = (~message, ~details, _children) => {
  ...component,
  render: _self =>
    <div className="error-view">
      <h5>
        <span className="error-message"> (ReasonReact.string(message)) </span>
        <span className="details"> (ReasonReact.string(details)) </span>
      </h5>
    </div>,
};
