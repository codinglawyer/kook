[%bs.raw {|require('./app.css')|}];

let str = ReasonReact.stringToElement;

let getValueFromEvent = (event) => ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value;

module Input = {
  let component = ReasonReact.reducerComponent("Input");
  let make = (~onSubmit, _children) => {
    ...component,
    initialState: () => "",
    reducer: (text, _state) => ReasonReact.Update(text),
    render: (self) =>
      <input
        onChange=(self.reduce((evt) => getValueFromEvent(evt)))
        onKeyDown=(
          (evt) =>
            if (ReactEventRe.Keyboard.key(evt) == "Enter") {
              onSubmit(self.state);
              (self.reduce(() => ""))()
            }
        )
      />
  };
};

module Form = {
  let component = ReasonReact.statelessComponent("Form");
  let make = (~onSubmit, _children) => {
    ...component,
    render: (_self) =>
      <div>
        <div> <div> (str("Title")) </div> <Input onSubmit /> </div>
        <div> <div> (str("Ingredients")) </div> <Input onSubmit /> </div>
      </div>
  };
};

type recipe = {
  name: string,
  ingredients: string
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
  | SaveInput(string);

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => {items: [{name: "Chilli Beed Lettuce Wraps", ingredients: "beef"}]},
  reducer: (action, state) =>
    switch action {
    | SaveInput(input) =>
      ReasonReact.Update({items: [{name: input, ingredients: "meat"}, ...state.items]})
    },
  render: (self) =>
    <div>
      <div className="titleContainer">
        <div className="title"> (str("Kook")) </div>
        <div className="subtitle"> (str("Your best cooking friend")) </div>
      </div>
      <Form onSubmit=(self.reduce((text) => SaveInput(text))) />
      <RecipeList recipes=self.state.items />
    </div>
};