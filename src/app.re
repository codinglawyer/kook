[%bs.raw {|require('./app.css')|}];

open RecipeForm;

open RecipeList;

open Utils;

open RecipeData;

type state = {recipes: list(recipe)};

type action =
  | SaveRecipe(recipe);

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => {
    recipes: [
      {
        id: (-1),
        title: "Chilli Beed Lettuce Wraps",
        ingredients: [{id: (-1), name: "Minced beef and pork"}]
      }
    ]
  },
  reducer: (action, state) =>
    switch action {
    | SaveRecipe(recipe) => ReasonReact.Update({recipes: [recipe, ...state.recipes]})
    },
  render: ({reduce, state}) =>
    <div>
      <div className="titleContainer">
        <div className="title"> (toString("Kook")) </div>
        <div className="subtitle"> (toString("Your best cooking friend")) </div>
      </div>
      <Form onSubmit=(reduce((recipe) => SaveRecipe(recipe))) />
      <RecipeList recipes=state.recipes />
    </div>
};