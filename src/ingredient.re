open Utils;
open RecipeData;

module Ingredient = {
  let component = ReasonReact.statelessComponent("Ingredient");
  let make = (~ingredient: ingredient, _children) => {
    ...component,
    render: (_self) =>
      <div key=(string_of_int(ingredient.id))> (toString(ingredient.name)) </div>,
  }
}