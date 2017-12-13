[%bs.raw {|require('./app.css')|}];

let str = ReasonReact.stringToElement;

let getValueFromEvent = (event) => ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value;

module Input = {
  type state = string;
  let component = ReasonReact.reducerComponent("Input");
  let make = (~save, ~value, ~placeholder, _children) => {
    ...component,
    initialState: () => "",
    reducer: (text, _s) => ReasonReact.Update(text),
    render: (_self) =>
      <div> <input placeholder value onChange=((evt) => save(getValueFromEvent(evt))) /> </div>
  };
};

type ingredient = {
  id: int,
  name: string
};

type recipe = {
  id: int,
  title: string,
  ingredients: list(ingredient)
};

let lastId = ref(0);

let newRecipe = (text) => {
  lastId := lastId^ + 1;
  {id: lastId^, title: text, ingredients: []}
};

/* create AddIngredientButton - it will add a new ingredient input */
module Form = {
  type state = {recipe:recipe};
  type action =
    | SaveNameInput(string)
    | SaveIngredientInput(string)
    | ClearForm(string)
    | AddIngredientByOne(int)
    | CreateNewRecipe(string);
  /* Form component - contains two input elements*/
  let component = ReasonReact.reducerComponent("Form");
  let make = (~onSubmit, _children) => {
    ...component,
    initialState: () => newRecipe(""),
    reducer: (action, state) =>
      switch action {
      | SaveNameInput(text) =>
      Js.log(state.id);
        ReasonReact.Update({id: state.id, title: text, ingredients: state.ingredients})
      | SaveIngredientInput(ingr) =>
        ReasonReact.Update({id: state.id, title: state.title, ingredients: [{name: ingr, id: 2}, ...state.ingredients]})
      | AddIngredientByOne(num) =>
        ReasonReact.Update({id: state.id, title: state.title, ingredients: [{name: "", id:3}, ...state.ingredients]})
      | ClearForm(text) =>
        Js.log(text);
        ReasonReact.Update({id: state.id, title: text, ingredients: []})
      | CreateNewRecipe(text) =>
        ReasonReact.Update(newRecipe(""))
      },
    render: (self) =>
      <div>
        <div>
          <div> (str("Title")) </div>
          <Input
            placeholder="Enter a title"
            value=self.state.title
            save=(self.reduce((text) => SaveNameInput(text)))
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
                      placeholder="Enter an ingredient name"
                      value=ingr.name
                      save=(self.reduce((ingr) => SaveIngredientInput(ingr.name)))
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
        <button onClick=(self.reduce((_) => AddIngredientByOne(1)))>
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
                          List.map((ingr: ingredient) => <div> (str(ingr.name)) </div>, recipe.ingredients)
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
      <Form onSubmit=(self.reduce((recipe) => {Js.log(self.state); SaveInput(recipe)})) />
      <RecipeList recipes=self.state.items />
    </div>
};