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

type recipe = {
  name: string,
  ingredients: list(string)
};

/* create AddIngredientButton - it will add a new ingredient input */
module Form = {
  type state = recipe;
  type action =
    | SaveNameInput(string)
    | SaveIngredientInput(string)
    | ClearForm(string)
    | AddIngredientByOne(int);
  /* Form component - contains two input elements*/
  let component = ReasonReact.reducerComponent("Form");
  let make = (~onSubmit, _children) => {
    ...component,
    initialState: () => {name: "", ingredients: []},
    reducer: (action, state) =>
      switch action {
      | SaveNameInput(text) =>
        Js.log(text);
        ReasonReact.Update({name: text, ingredients: state.ingredients})
      | SaveIngredientInput(ingr) =>
        ReasonReact.Update({name: state.name, ingredients: [ingr, ...state.ingredients]})
      | AddIngredientByOne(num) =>
        ReasonReact.Update({name: state.name, ingredients: ["", ...state.ingredients]})
      | ClearForm(text) =>
        Js.log(text);
        ReasonReact.Update({name: text, ingredients: []})
      },
    render: (self) =>
      <div>
        <div>
          <div> (str("Title")) </div>
          <Input
            placeholder="Enter a title"
            value=self.state.name
            save=(self.reduce((text) => SaveNameInput(text)))
          />
        </div>
        <div>
          <div> (str("Ingredients")) </div>
          (
            ReasonReact.arrayToElement(
              Array.of_list(
                List.map(
                  (ingr) =>
                    <Input
                      placeholder="Enter an ingredient name"
                      value=ingr
                      save=(self.reduce((ingr) => SaveIngredientInput(ingr)))
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
              onSubmit(self.state);
              (self.reduce((__) => ClearForm("")))()
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
                    <div> (str("Name:" ++ recipe.name)) </div>
                    <div> (str("Ingredients:")) </div>
                    (
                      ReasonReact.arrayToElement(
                        Array.of_list(
                          List.map((ingr) => <div> (str(ingr)) </div>, recipe.ingredients)
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
  initialState: () => {items: [{name: "Chilli Beed Lettuce Wraps", ingredients: ["beef"]}]},
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
      <Form onSubmit=(self.reduce((recipe) => SaveInput(recipe))) />
      <RecipeList recipes=self.state.items />
    </div>
};