let getValueFromEvent = (event) : string => ReactDOMRe.domElementToObj(
  ReactEventRe.Form.target(event)
)##value;


module Input = {
  type state = string;
  let component = ReasonReact.statelessComponent("Input");
  let make = (~save, ~value, ~placeholder, _children) => {
    ...component,
    render: (_self) =>
      <div> <input placeholder value onChange=((evt) => save(getValueFromEvent(evt))) /> </div>
  };
};