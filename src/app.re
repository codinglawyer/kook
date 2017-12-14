[%bs.raw {|require('./app.css')|}];

open Input;

let str = ReasonReact.stringToElement;

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

/* create AddIngredientButton - it will add a new ingredient input */
module Form = {
  type state = {recipe};
  type action =
    | SaveNameInput(string, int)
    | SaveIngredientInput(string, int)
    | ClearForm(string)
    | CreateNewRecipe(string)
    | CreateNewIngredient(string);
  /* Form component - contains two input elements*/
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
        /* <Input
             value=self.state.ingredients
             save=(self.reduce((ingr) => SaveIngredientInput(ingr)))
           />
           <Input
             value=self.state.ingredients
             save=(self.reduce((ingr) => SaveIngredientInput(ingr)))
           /> */
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