open Utils;
open RecipeData;
open Ingredient;

module Recipe = {
  let component = ReasonReact.statelessComponent("Recipe");
  let make = (~recipe, _children) => {
    ...component,
    render: (_self) =>
    <div key=(string_of_int(recipe.id))>
      <div> (toString("Name:" ++ recipe.title)) </div>
      <div> (toString("Ingredients:")) </div>
      (
        ReasonReact.arrayToElement(
          Array.of_list(
            List.map(
              (ingr: ingredient) =>
                <Ingredient ingredient=ingr/>,
              recipe.ingredients
            )
          )
        )
      )
    </div>
  }
}