[%bs.raw {|require('./app.css')|}];

let str = ReasonReact.stringToElement;

let getValueFromEvent = (event) => ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value;

module Input = {
  let component = ReasonReact.statelessComponent("Input");
  let make = (~save,_children) => {
    ...component,
    render: (_self) =>
      <div>
        <input
          onChange=((evt) => save(getValueFromEvent(evt)))
        />
      </div>
  };
};

type recipe = {
  name: string,
  ingredients: string
};


module Form = {
  type state = recipe;

  type action =
    | SaveNameInput(string)
    | SaveIngredientInput(string);

  let component = ReasonReact.reducerComponent("Form");
  let make = (~onSubmit, _children) => {
    ...component,
    initialState: () => {name: "Name", ingredients: "ingredient" },
    reducer: (action, state) =>
      switch action {
      | SaveNameInput(text) => ReasonReact.Update({name: text, ingredients: state.ingredients})
      | SaveIngredientInput(ingr) => ReasonReact.Update({name: state.name, ingredients: ingr})
    },
    render: (self) =>
      <div>
        <div> <div> (str("Title")) </div> <Input save=(self.reduce((text) => SaveNameInput(text))) /> </div>
        <div> <div> (str("Ingredients")) </div> <Input save=(self.reduce((ingr) => SaveIngredientInput(ingr))) /> </div>
        <button onClick=((_) => onSubmit(self.state))
        > (str("Save recipe")) </button>
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
                    <div> (str("Ingredients:" ++ recipe.ingredients)) </div>
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
  initialState: () => {items: [{name: "Chilli Beed Lettuce Wraps", ingredients: "beef"}]},
  reducer: (action, state) =>
    switch action {
    | SaveInput(recipe) =>
      ReasonReact.Update({items: [recipe, ...state.items]})
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