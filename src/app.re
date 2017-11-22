[%bs.raw {|require('./app.css')|}];

let str = ReasonReact.stringToElement;

let getValueFromEvent = (event) => ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value;

module Input = {
  let component = ReasonReact.reducerComponent("Input");
  let make = (~onSubmit, _children) => {
    ...component,
    initialState: () => "",
    reducer: (text, _state) => ReasonReact.Update(text),
    render: (self) => <input
      onChange=(self.reduce((evt) => getValueFromEvent(evt)))
      onKeyDown=((evt) =>
      if (ReactEventRe.Keyboard.key(evt) == "Enter") {
        onSubmit(self.state);
        (self.reduce(() => ""))()
      })
    />
  }
};

module Form = {
  let component = ReasonReact.statelessComponent("Form");
  let make = (~onSubmit, _children) => {
    ...component,
    render: (_self) =>
      <div>
        <div>
          <div>(str("Title"))</div>
          <Input onSubmit/>
        </div>
        <div>
          <div>(str("Ingredients"))</div>
          <Input onSubmit/>
        </div>
      </div>
      }
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
            (
              List.map((recipe) => <div>(str(recipe))</div>, recipes)
            )
          )
        )
      )
        </div>
  }
};

type state = {items: list(string)};
type action =
  | SaveInput(string);

let component = ReasonReact.reducerComponent("App");



let make = (_children) => {
  ...component,
  initialState: () => {items: ["Chilli Beed Lettuce Wraps", "Chilli Con Carne", "Lasagna", "Putanesca"]},
  reducer: (action, state) =>
    switch action{
    | SaveInput(input) => ReasonReact.Update({items: [input, ...state.items]})
    },
  render: (self) =>
    <div>
      <div className="titleContainer">
        <div className="title">(str("Kook"))</div>
        <div className="subtitle">(str("Your best cooking friend"))</div>
      </div>
      <Form onSubmit=(self.reduce((text) => SaveInput(text)))/>
      <RecipeList recipes=(self.state.items) />
    </div>
};