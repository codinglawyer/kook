[%bs.raw {|require('./app.css')|}];

let str = ReasonReact.stringToElement;

module RecipeList ={
  let component = ReasonReact.statelessComponent("RecipeList");
  let make = (_children) => {
    ...component,
    render: (_self) => <div>(str("Recipe List"))</div>
  }
};


let component = ReasonReact.statelessComponent("App");

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div>
      <div className="titleContainer">
        <div className="title">(str("Kook"))</div>
        <div className="subtitle">(str("Your best cooking friend"))</div>
      </div>
      <RecipeList />
    </div>
};