open Friend;

let component = ReasonReact.statelessComponent("FriendList");

let make = (~friends, _children) => {
  ...component,
  render: _self =>
    <div>
      <ul className="friend-list">
        (
          ReasonReact.array(
            Array.of_list(friends)
            |> Array.map(friend =>
                 <li
                   key=(string_of_int(friend.id))
                   className="friend-list-item">
                   <div className="friend">
                     (ReasonReact.string(friend.name))
                     <span className="username">
                       (ReasonReact.string(" @" ++ friend.username))
                     </span>
                   </div>
                 </li>
               ),
          )
        )
      </ul>
    </div>,
};
