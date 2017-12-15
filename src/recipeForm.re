open Input;

open RecipeData;

open Utils;

module Form = {
  type state = recipe;
  type action =
    | SaveRecipeName(string, int)
    | SaveIngredientName(string, int)
    | CreateNewRecipe(string)
    | CreateNewIngredient(string);
  let component = ReasonReact.reducerComponent("Form");
  let make = (~onSubmit, _children) => {
    ...component,
    initialState: () => createRecipe(""),
    reducer: (action, state) =>
      switch action {
      | SaveRecipeName(name, _recipeId) => ReasonReact.Update({...state, title: name})
      | SaveIngredientName(ingredientName, ingredientId) =>
        let updatedIngredients =
          List.map(
            (ingredient: ingredient) =>
              ingredient.id === ingredientId ? {...ingredient, name: ingredientName} : ingredient,
            state.ingredients
          );
        ReasonReact.Update({...state, ingredients: updatedIngredients})
      | CreateNewRecipe(title) => ReasonReact.Update(createRecipe(title))
      | CreateNewIngredient(name) =>
        ReasonReact.Update({...state, ingredients: [createIngredient(name), ...state.ingredients]})
      },
    render: ({state, reduce}) =>
      <div>
        <div> (toString("Title")) </div>
        <Input
          placeholder="Enter a title"
          value=state.title
          save=(reduce((recipeName) => SaveRecipeName(recipeName, state.id)))
        />
        <div> (toString("Ingredients")) </div>
        (
          ReasonReact.arrayToElement(
            Array.of_list(
              List.map(
                (ingr: ingredient) =>
                  <Input
                    key=(string_of_int(ingr.id))
                    placeholder="Enter an ingredient name"
                    value=ingr.name
                    save=(reduce((ingredientName) => SaveIngredientName(ingredientName, ingr.id)))
                  />,
                state.ingredients
              )
            )
          )
        )
        <button onClick=(reduce((_) => CreateNewIngredient("")))>
          (toString("Add new ingredient"))
        </button>
        <button
          onClick=(
            (_) => {
              onSubmit(state);
              (reduce((__) => CreateNewRecipe("")))()
            }
          )>
          (toString("Save recipe"))
        </button>
      </div>
  };
};