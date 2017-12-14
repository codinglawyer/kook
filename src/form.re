open Input;
open RecipeData;
open Utils;

module Form = {
  type state = {recipe};
  type action =
    | SaveNameInput(string, int)
    | SaveIngredientInput(string, int)
    | ClearForm(string)
    | CreateNewRecipe(string)
    | CreateNewIngredient(string);
  let component = ReasonReact.reducerComponent("Form");
  let make = (~onSubmit, _children) => {
    ...component,
    initialState: () => newRecipe(""),
    reducer: (action, state) =>
      switch action {
      | SaveNameInput(text, _recipeId) =>
        ReasonReact.Update({id: state.id, title: text, ingredients: state.ingredients})
      | SaveIngredientInput(ingredientName, ingredientId) =>
        let updatedIngredients =
          List.map(
            (ingredient: ingredient) =>
              ingredient.id === ingredientId ?
                {name: ingredientName, id: ingredient.id} : ingredient,
            state.ingredients
          );
        ReasonReact.Update({id: state.id, title: state.title, ingredients: updatedIngredients})
      | ClearForm(text) =>
        Js.log(text);
        ReasonReact.Update({id: state.id, title: text, ingredients: []})
      | CreateNewRecipe(text) => ReasonReact.Update(newRecipe(""))
      | CreateNewIngredient(text) =>
        Js.log(state.ingredients);
        ReasonReact.Update({
          id: state.id,
          title: state.title,
          ingredients: [newIngr(""), ...state.ingredients]
        })
      },
    render: (self) =>
      <div>
        <div>
          <div> (str("Title")) </div>
          <Input
            placeholder="Enter a title"
            value=self.state.title
            save=(self.reduce((text) => SaveNameInput(text, self.state.id)))
          />
        </div>
        <div>
          <div> (str("Ingredients")) </div>
          (
            ReasonReact.arrayToElement(
              Array.of_list(
                List.map(
                  (ingr: ingredient) =>
                    <Input
                      key=(string_of_int(ingr.id))
                      placeholder="Enter an ingredient name"
                      value=ingr.name
                      save=(self.reduce((ingrName) => SaveIngredientInput(ingrName, ingr.id)))
                    />,
                  self.state.ingredients
                )
              )
            )
          )
        </div>
        <button onClick=(self.reduce((_) => CreateNewIngredient("s")))>
          (str("Add new ingredient"))
        </button>
        <button
          onClick=(
            (_) => {
              Js.log(self.state.ingredients);
              onSubmit(self.state);
              (self.reduce((__) => CreateNewRecipe("s")))()
            }
          )>
          (str("click"))
        </button>
      </div>
  };
};