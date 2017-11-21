[%bs.raw {|require('./app.css')|}];

let str = ReasonReact.stringToElement;

type action =
  | SaveInput(string);


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
        onSubmit(self.state)
      })
    />
  }
};

type recipes = List;
let recipes = ["Chilli Beed Letuce Wraps", "Chilli Con Carne", "Lasagna", "Putanesca"];

module RecipeList = {
  let component = ReasonReact.statelessComponent("RecipeList");
  let make = (_children) => {
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


let component = ReasonReact.reducerComponent("App");



let make = (_children) => {
  ...component,
  initialState: () => "",
  reducer: (action, _state) =>
    switch action{
    | SaveInput(text) => {Js.log(text); ReasonReact.Update(text)}
    },
  render: (self) =>
    <div>
      <div className="titleContainer">
        <div className="title">(str("Kook"))</div>
        <div className="subtitle">(str("Your best cooking friend"))</div>
      </div>
      <Input onSubmit=(self.reduce((text) => SaveInput(text)))/>
      <RecipeList />
    </div>
};