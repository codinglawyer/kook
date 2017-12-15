type ingredient = {
  id: int,
  name: string
};

type recipe = {
  id: int,
  title: string,
  ingredients: list(ingredient)
};

let lastRecipeId = ref(0);

let createRecipe = title => {
  lastRecipeId := lastRecipeId^ + 1;
  {id: lastRecipeId^, title, ingredients: []}
};

let lastIngredientId = ref(0);

let createIngredient = name => {
  lastIngredientId := lastIngredientId^ + 1;
  {id: lastIngredientId^, name}
};
