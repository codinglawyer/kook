[%bs.raw {|require('./app.css')|}];

open Form;
open Utils;
open RecipeData;

module RecipeList = {
  let component = ReasonReact.statelessComponent("RecipeList");
  let make = (~recipes, _children) => {
    ...component,
    render: (_self) =>
      <div>
        (
          ReasonReact.arrayToElement(
            Array.of_list(
              List.map(
                (recipe) =>
                  <div>
                    <div> (str("Name:" ++ recipe.title)) </div>
                    <div> (str("Ingredients:")) </div>
                    (
                      ReasonReact.arrayToElement(
                        Array.of_list(
                          List.map(
                            (ingr: ingredient) =>
                              <div key=(string_of_int(ingr.id))> (str(ingr.name)) </div>,
                            recipe.ingredients
                          )
                        )
                      )
                    )
                  </div>,
                recipes
              )
            )
          )
        )
      </div>
  };
};

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