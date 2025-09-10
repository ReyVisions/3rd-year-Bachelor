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
/// Modifié par YE Frédéric le 26/03/2023
/// Modifie par Remy XU le 03/04/2023
/// </summary>
public class IdleAgentAction : AgentAction {

    /// <summary>
    /// Permet d'initialiser l'attribut _agent.
    /// </summary>
    /// <param name="agent">
    /// L'agent sur lequel l'action est réalisée.
    /// </param>
    public IdleAgentAction(Agent agent) : base(agent) { }

    /// <summary>
    /// Dans cet fonction, il est vérifié si l'agent
    /// a bien changé d'animation, qu'il n'a plus de
    /// destination.
    /// 
    /// Fait par EL MONTASER Osmane le 10/04/2022.
    /// Modifié par YE Frédéric le 26/03/2023
    /// Modifie par Remy XU le 03/04/2023
    /// </summary>
    public override void update() {
        /*if(!_agent.Attributes["SpeciesName"].Equals("Grass"))
            Debug.Log("Idling... EnergyNeeds = " + _agent.Attributes["EnergyNeeds"] + "\n Stamina = " + _agent.Attributes["Stamina"]);*/
        /*if(_agent.Attributes["SpeciesName"].Equals("Grass"))
            Debug.Log("Idling Grass... " + _agent.Attributes["EnergyNeeds"]);*/

        if (!_agent.Attributes["SpeciesName"].Equals("Grass"))
        {
            if (_agent.GetComponent<UnityEngine.AI.NavMeshAgent>().enabled == true)
            {
                _agent.AgentMesh.isStopped = false;
            }
        }
        
        if(_agent.Attributes["SpeciesName"].Equals("Grass") && Convert.ToDouble(_agent.Attributes["EnergyNeeds"]) > 0)
            _agent.Attributes["EnergyNeeds"] = (Convert.ToDouble(_agent.Attributes["EnergyNeeds"]) - (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.ENERGY_FACTOR) * 2f).ToString();
        else {
            //Gestion de l'endurence lors du sprint
            if (ManualControl.isSprinting == true)
            {
                _agent.Attributes["Stamina"] = (Convert.ToDouble(_agent.Attributes["Stamina"]) - 3 * (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.STAMINA_FACTOR) * GameObject.Find("Terrain").GetComponent<SeasonManager>().statusConsumption("Stamina")).ToString();
            }
            else
            {
                _agent.Attributes["Stamina"] = (Convert.ToDouble(_agent.Attributes["Stamina"]) - (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.STAMINA_FACTOR) * GameObject.Find("Terrain").GetComponent<SeasonManager>().statusConsumption("Stamina")).ToString();
            }
            _agent.Attributes["EnergyNeeds"] = (Convert.ToDouble(_agent.Attributes["EnergyNeeds"]) + (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.ENERGY_FACTOR) * GameObject.Find("Terrain").GetComponent<SeasonManager>().statusConsumption("EnergyNeeds")).ToString();
            _agent.Attributes["WaterNeeds"] = (Convert.ToDouble(_agent.Attributes["WaterNeeds"]) + (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.WATER_FACTOR) * GameObject.Find("Terrain").GetComponent<SeasonManager>().statusConsumption("WaterNeeds")).ToString();
            if (_agent.PredateursVisible() == true)
                _agent.Attributes["Fear"] = (Convert.ToDouble(_agent.Attributes["Fear"]) + (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.FEAR_FACTOR * 2000)).ToString();
            else
                _agent.Attributes["Fear"] = (Convert.ToDouble(_agent.Attributes["Fear"]) - (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.FEAR_FACTOR) * 400).ToString();
            if (Convert.ToDouble(_agent.Attributes["Fear"]) < 0)
            {
                _agent.Attributes["Fear"] = 0.ToString();
            }
            if (Convert.ToDouble(_agent.Attributes["Fear"]) > 1)
            {
                _agent.Attributes["Fear"] = 1.ToString();
            }
            if (Convert.ToDouble(_agent.Attributes["Stamina"]) < 0)
            {
                _agent.Attributes["Stamina"] = 0.ToString();
            }
            if (Convert.ToDouble(_agent.Attributes["Stamina"]) > 1)
            {
                _agent.Attributes["Stamina"] = 1.ToString();
            }
            if (bool.Parse(_agent.Attributes["IsAlive"]))
                _agent.Attributes["Health"] = (Convert.ToDouble(_agent.Attributes["Health"]) + (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.HEALING_FACTOR)).ToString();
            if ((Convert.ToDouble(_agent.Attributes["Health"]) > (Convert.ToDouble(_agent.Attributes["MaxHealth"]))))
            {
                _agent.Attributes["Health"] = _agent.Attributes["MaxHealth"];
            }
        }
        if (!_agent.Attributes["SpeciesName"].Equals("Grass"))
        {
            if (_agent.GetComponent<UnityEngine.AI.NavMeshAgent>().enabled == true
            && (_agent.AgentMesh != null)
            && (_agent.mimetismesleep == false))/*
            && (!_agent.AgentMesh.pathPending
            && _agent.AgentMesh.remainingDistance <= _agent.AgentMesh.stoppingDistance
            && (!_agent.AgentMesh.hasPath || _agent.AgentMesh.velocity.sqrMagnitude == 0f)))*/
            {
                _agent.walker();
                UnityEngine.Debug.Log("Je Suis dans walker idle");
            }
        }
        if(!_agent.Attributes["SpeciesName"].Equals("Grass") && !_agent.Animation.GetBool("WalkTrigger"))
            handleAnimation();
        //throw new NotImplementedException();
    }

    private void handleAnimation() {
        _agent.Animation.SetTrigger("WalkTrigger");
        _agent.Animation.ResetTrigger("DeadTrigger");
        _agent.Animation.ResetTrigger("AttackTrigger");
        _agent.Animation.ResetTrigger("EatTrigger");
        _agent.Animation.ResetTrigger("IdleTrigger");
    }
}