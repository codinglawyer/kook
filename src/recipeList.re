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
                  <div key=(string_of_int(recipe.id))>
                    <div> (toString("Name:" ++ recipe.title)) </div>
                    <div> (toString("Ingredients:")) </div>
                    (
                      ReasonReact.arrayToElement(
                        Array.of_list(
                          List.map(
                            (ingr: ingredient) =>
                              <div key=(string_of_int(ingr.id))> (toString(ingr.name)) </div>,
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