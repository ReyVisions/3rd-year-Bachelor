using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using TreeEditor;



/// <summary>
/// Classe inspirée de ChoosePreyAgentAction pour attaquer un agent proche de lui
/// lorsqu'il est en mode manuel.
/// 
/// Fait par Remy XU le 30/03/2023
/// </summary>
public class EatToggle: MonoBehaviour
{
    private Agent _agent;

    [SerializeField] private GameObject EatToggler;

    private GameObject ManualControlToggler;
    private bool _isChasing;

    /// <summary>
    /// Variables pour changer et stocker l'action en cours lorsqu'on passe en mode manuel.
    /// </summary>
    public ActionTreeNode<AgentAction> previousAction;

    // Start is called before the first frame update
    void Start()
    {
        ManualControlToggler = ManualControl.FindChildGameObjectByName(GameObject.Find("Canvas"), "ManualControlToggle");
    }

    // Update is called once per frame
    void Update()
    {
        if (ManualControlToggler.GetComponent<UnityEngine.UI.Toggle>().isOn)
        {
            _isChasing = EatToggler.GetComponent<UnityEngine.UI.Toggle>().isOn;
            _agent = GameObject.Find("AgentManager").GetComponent<AgentStatsGUIUpdater>().AgentToTrack;
            if (_isChasing)
            {
                //Debug.Log("Chasing prey...  EnergyNeeds = " + _agent.Attributes["EnergyNeeds"]);
                _agent.Attributes["Stamina"] = (Convert.ToDouble(_agent.Attributes["Stamina"]) - (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.STAMINA_FACTOR)).ToString();
                _agent.Attributes["EnergyNeeds"] = (Convert.ToDouble(_agent.Attributes["EnergyNeeds"]) + (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.ENERGY_FACTOR)).ToString();
                _agent.Attributes["WaterNeeds"] = (Convert.ToDouble(_agent.Attributes["WaterNeeds"]) + (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.WATER_FACTOR)).ToString();
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
                chasserManuellement();
            }
        }
    }
    private void chasserManuellement()
    {
        //_agent est l'agent qui vaut manger, animal Temp celui qui va se faire manger.
        Agent animalTemp = ProieLaPlusProche(_agent);
        //Debug.Log(animalTemp);

        if (animalTemp != null)
        {
            float dist = Vector3.Distance(_agent.transform.position, animalTemp.transform.position);
            //UnityEngine.Debug.Log("Je suis avt manger"+ dist + "je suis " + _agent.transform.position + "je vais " + _agent.AgentCible.transform.position);
            if (dist <= 2.5f)
            {
                //UnityEngine.Debug.Log("J'ai la distance pour manger");

                if (bool.Parse(animalTemp.Attributes["IsAlive"])) // si la cible est en vie
                {
                    Debug.Log("Jattaque");
                    attackAnimation();
                    animalTemp.Attributes["Health"] = (Convert.ToDouble(animalTemp.Attributes["Health"]) - Convert.ToDouble(_agent.Attributes["Ad"])).ToString(); //l'agent attaque la cible
                                                                                                                                                                  // rajouter les anim si dispo
                }
                else if (Convert.ToDouble(animalTemp.Attributes["CarcassEnergyContribution"]) >= 10.0)
                {
                    Debug.Log("Je mange");
                    eatAnimation();
                    animalTemp.Attributes["CarcassEnergyContribution"] = (Convert.ToDouble(animalTemp.Attributes["CarcassEnergyContribution"]) - 0.5).ToString();
                    _agent.Attributes["EnergyNeeds"] = (Convert.ToDouble(_agent.Attributes["EnergyNeeds"]) - 0.5).ToString();
                    if (Convert.ToDouble(_agent.Attributes["EnergyNeeds"]) < 0.0)
                        _agent.Attributes["EnergyNeeds"] = (0.0).ToString();
                }
            }
        }
    }

    /// <summary>
    /// Methode qui calcule sa proie la plus proche parmi ceux qu'il voit.
    ///Fait par Remy Xu le 30/03/2023.
    /// </summary>
    /// <param name="agent"> Agent dont on regarde la proie la plus proche. </param>
    /// <returns> Renvoie l'agent le plus proche s'il y en a au moins 1, sinon null </returns>
    public Agent ProieLaPlusProche(Agent agent)
    {
        if (agent.AnimauxEnVisuel.Count==0)
        {
            return (null);
        }
        else if (agent.AnimauxEnVisuel.Count == 1)
        {
            return (agent.AnimauxEnVisuel[0].GetComponent<Agent>());
        }
        else
        {
            float distMin = Vector3.Distance(_agent.transform.position, agent.AnimauxEnVisuel[0].GetComponent<Agent>().transform.position);
            float dist;
            Agent agentDistMin= agent.AnimauxEnVisuel[0].GetComponent<Agent>();

            for (int i = 0; i < agent.AnimauxEnVisuel.Count; i++)
            {
                dist = Vector3.Distance(_agent.transform.position, agent.AnimauxEnVisuel[i].GetComponent<Agent>().transform.position);
                if (agent.AnimauxEnVisuel[i] != null)
                {
                    dist = Vector3.Distance(_agent.transform.position, agent.AnimauxEnVisuel[i].GetComponent<Agent>().transform.position);
                    if (dist < distMin)
                    {
                        distMin = dist;
                        agentDistMin = agent.AnimauxEnVisuel[i].GetComponent<Agent>();
                    }
                }
            }
            return agentDistMin;
        }
    }

    /// <summary>
    /// Methodes recuperees de ChoosePreyAgentAction
    /// 30/03/2023
    /// </summary>
    private void eatAnimation()
    {
        if (!_agent.Animation.GetBool("EatTrigger"))
        {
            _agent.Animation.ResetTrigger("AttackTrigger");
            _agent.Animation.SetTrigger("EatTrigger");
        }
    }
    private void attackAnimation()
    {
        if (!_agent.Animation.GetBool("AttackTrigger"))
        {
            _agent.Animation.ResetTrigger("IdleTrigger");
            _agent.Animation.SetTrigger("AttackTrigger");
        }
    }
    /// <summary>
    /// Modifie le nom de l'action quand on passe en mode manuel.
    /// FAit par Remy XU le 07/04/2023-09/04/2023
    /// </summary>
    public void ManualEatAction()
    {
        if (EatToggler.GetComponent<UnityEngine.UI.Toggle>().isOn)
        {
            //Debug.Log(EatToggler.GetComponent<UnityEngine.UI.Toggle>().isOn);
            int i = 0;
            
            previousAction = _agent._currentAction;
            _agent._currentAction = _agent._currentAction.Parent;
            
            foreach (ActionTreeNode<AgentAction> action in _agent._currentAction.Children)
            {
                if (i == 6)
                {  
                    action.Parent = _agent. _currentAction;
                    _agent._currentAction = action;
                    //UnityEngine.Debug.Log(_agent._currentAction.Action.GetType().Name);
                    //UnityEngine.Debug.Log("Je cherche de la nourriture");
                }
                i++;
            }
        }
        else
        {
            _agent._currentAction = previousAction;
        }
    }
}
