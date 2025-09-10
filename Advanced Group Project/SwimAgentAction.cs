using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SwimAgentAction : AgentAction {
    private GameObject _child;
    /// <summary>
    /// Permet d'initialiser l'attribut _agent.
    /// </summary>
    /// <param name="agent">
    /// L'agent sur lequel l'action est réalisée.
    /// </param>
    public SwimAgentAction(Agent agent) : base(agent) { }
    // Start is called before the first frame update

    // Update is called once per frame
    public override void update()
    {
        //Permet a l'agent de perdre plus de Stamina que habituellement (à regler pour que cela soit logique )
        _agent.Attributes["Stamina"] = (Convert.ToDouble(_agent.Attributes["Stamina"]) + (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.STAMINA_FACTOR*2)).ToString();
        swim();
        
    }

    private void swim()
    {
        
    }


}
