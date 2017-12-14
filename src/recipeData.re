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

let newRecipe = (text) => {
  lastRecipeId := lastRecipeId^ + 1;
  {id: lastRecipeId^, title: text, ingredients: []}
};

let lastIngrId = ref(0);

let newIngr = (text) => {
  lastIngrId := lastIngrId^ + 1;
  {id: lastIngrId^, name: text}
};
