using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

/// <summary>
/// Classe qui permet de déterminer toutes les
/// actions à faire lorsque l'agent est dans l'état
/// "Idle".
/// Lorsque l'agent est dans cet état, il ne bouge
/// plus et est dans l'attente d'une nouvelle
/// action à réaliser.
/// 
/// Fait par EL MONTASER Osmane le 10/04/2022. 
/// </summary>
public class SleepAgentAction : AgentAction {

    /// <summary>
    /// Permet d'initialiser l'attribut _agent.
    /// </summary>
    /// <param name="agent">
    /// L'agent sur lequel l'action est réalisée.
    /// </param>
    public SleepAgentAction(Agent agent) : base(agent) { }

    /// <summary>
    /// Dans cet fonction, TODO
    /// 
    /// Fait par EL MONTASER Osmane le 10/04/2022.
    /// Conditions NavMeshAgent par Remy Xu 29/03/2023 et 03/04/2023.
    /// Modifié par YE Frédéric le 26/03/2023
    /// </summary>
    public override void update() {
        //Debug.Log("Sleeping ... Stamina = " + _agent.Attributes["Stamina"]);
        if (!_agent.Attributes["SpeciesName"].Equals("Grass")) //Desactive les fonctions utilisant la Navmesh si on est en mode manuel
        {
            if (_agent.GetComponent<UnityEngine.AI.NavMeshAgent>().enabled == true) //Desactive les fonctions utilisant la Navmesh si on est en mode manuel
            {
                _agent.AgentMesh.isStopped = false;
                if (_agent.AgentMesh.destination != _agent.transform.position)
                    _agent.AgentMesh.SetDestination(_agent.transform.position);
            }
        }
        //Gestion de l'endurence lors du sprint
        if (ManualControl.isSprinting == true)
        {
            _agent.Attributes["Stamina"] = (Convert.ToDouble(_agent.Attributes["Stamina"]) + 5 * (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.STAMINA_FACTOR) * GameObject.Find("Terrain").GetComponent<SeasonManager>().statusConsumption("Stamina")).ToString();
        }
        else
        {
            _agent.Attributes["Stamina"] = (Convert.ToDouble(_agent.Attributes["Stamina"]) + 5 *  (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.STAMINA_FACTOR) * GameObject.Find("Terrain").GetComponent<SeasonManager>().statusConsumption("Stamina")).ToString();
        }
        _agent.Attributes["Stamina"] = (Convert.ToDouble(_agent.Attributes["Stamina"]) + 5 * (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.STAMINA_FACTOR) * GameObject.Find("Terrain").GetComponent<SeasonManager>().statusConsumption("Stamina")).ToString();
        _agent.Attributes["EnergyNeeds"] = (Convert.ToDouble(_agent.Attributes["EnergyNeeds"]) + (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.ENERGY_FACTOR) * GameObject.Find("Terrain").GetComponent<SeasonManager>().statusConsumption("EnergyNeeds")).ToString();
        _agent.Attributes["WaterNeeds"] = (Convert.ToDouble(_agent.Attributes["WaterNeeds"]) + (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.WATER_FACTOR) * GameObject.Find("Terrain").GetComponent<SeasonManager>().statusConsumption("WaterNeeds")).ToString();
        _agent.Attributes["Fear"] = (Convert.ToDouble(_agent.Attributes["Fear"]) - (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.FEAR_FACTOR * 3000)).ToString();
        if (Convert.ToDouble(_agent.Attributes["Fear"]) < 0)
        {
            _agent.Attributes["Fear"] = 0.ToString();
        }
        if (Convert.ToDouble(_agent.Attributes["Fear"]) > 100)
        {
            _agent.Attributes["Fear"] = 1.ToString();
        }
        if (Convert.ToDouble(_agent.Attributes["Stamina"]) > 1)
        {
            _agent.Attributes["Stamina"] = 1.ToString();
            _agent.GetComponent<UnityEngine.AI.NavMeshAgent>().enabled = true;
        }
        if (Convert.ToDouble(_agent.Attributes["Stamina"]) < 0)
        {
            _agent.Attributes["Stamina"] = 0.ToString();
        }
        if (bool.Parse(_agent.Attributes["IsAlive"]))
            _agent.Attributes["Health"] = (Convert.ToDouble(_agent.Attributes["Health"]) + (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.HEALING_FACTOR)).ToString();
        if ((Convert.ToDouble(_agent.Attributes["Health"]) > (Convert.ToDouble(_agent.Attributes["MaxHealth"]))))
        {
            _agent.Attributes["Health"] = _agent.Attributes["MaxHealth"];
        }

        _agent.GetComponent<UnityEngine.AI.NavMeshAgent>().enabled = false;
        if (!_agent.Animation.GetBool("IdleTrigger"))
            handleAnimation();
    }

    private void handleAnimation() {
        _agent.Animation.ResetTrigger("WalkTrigger");
        _agent.Animation.ResetTrigger("DeadTrigger");
        _agent.Animation.ResetTrigger("AttackTrigger");
        _agent.Animation.ResetTrigger("EatTrigger");
        _agent.Animation.SetTrigger("IdleTrigger");
    }
}