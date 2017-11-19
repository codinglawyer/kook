[%bs.raw {|require('./app.css')|}];

let str = ReasonReact.stringToElement;

let component = ReasonReact.statelessComponent("App");

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div className="titleContainer">
      <div className="title">(str("Kook"))</div>
      <div className="subtitle">(str("Your best cooking friend"))</div>
    </div>
};