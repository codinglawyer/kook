[%bs.raw {|require('./app.css')|}];

open Form;

open RecipeList;

open Utils;

open RecipeData;


type state = {items: list(recipe)};

type action =
  | SaveInput(recipe);

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => {
    items: [{id: 2, title: "Chilli Beed Lettuce Wraps", ingredients: [{id: 1, name: "beef"}]}]
  },
  reducer: (action, state) =>
    switch action {
    | SaveInput(recipe) => ReasonReact.Update({items: [recipe, ...state.items]})
    },
  render: (self) =>
    <div>
      <div className="titleContainer">
        <div className="title"> (str("Kook")) </div>
        <div className="subtitle"> (str("Your best cooking friend")) </div>
      </div>
      <Form
        onSubmit=(
          self.reduce(
            (recipe) => {
              Js.log(self.state);
              SaveInput(recipe)
            }
          )
        )
      />
      <RecipeList recipes=self.state.items />
    </div>
};