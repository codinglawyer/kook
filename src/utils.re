let getValueFromEvent = (event) : string => ReactDOMRe.domElementToObj(
                                              ReactEventRe.Form.target(event)
                                            )##value;