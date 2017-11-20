[%bs.raw {|require('./app.css')|}];

let str = ReasonReact.stringToElement;

type recipes = List;

let recipes = ["Chilli Beed Letuce Wraps", "Chilli Con Carne", "Lasagna", "Putanesca"];

module RecipeList ={
  let component = ReasonReact.statelessComponent("RecipeList");
  let make = (_children) => {
    ...component,
    render: (_self) =>
      <div>
      (
        ReasonReact.arrayToElement(
          Array.of_list(
            (
              List.map((recipe) => <div>(str(recipe))</div>, recipes)
            )
          )
        )
      )
        </div>
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