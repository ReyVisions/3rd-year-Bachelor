using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using TreeEditor;

/// <summary>
/// CLasse pour faire dormir un agent manuellement
/// 
/// Fait par Remy Xu le 30/03/2023
/// </summary>
public class SleepToggle : MonoBehaviour
{

    [SerializeField] private GameObject SleepToggler;

    private GameObject ManualControlToggler;
    private Agent _agent;
    private bool _isSleeping;

    /// <summary>
    /// Variables pour changer et stocker l'action en cours lorsqu'on passe en mode manuel.

    public ActionTreeNode<AgentAction> previousAction;


    void Start()
    {
        ManualControlToggler = ManualControl.FindChildGameObjectByName(GameObject.Find("Canvas"), "ManualControlToggle");
    }


    void Update()
    {
        
        if (ManualControlToggler.GetComponent<UnityEngine.UI.Toggle>().isOn)
        {

            _isSleeping = SleepToggler.GetComponent<UnityEngine.UI.Toggle>().isOn;
            _agent = GameObject.Find("AgentManager").GetComponent<AgentStatsGUIUpdater>().AgentToTrack;
            if (_isSleeping && Convert.ToDouble(_agent.Attributes["Stamina"]) < 1)
            {
                
                //Empeche le contrôle


                //Augmentation de la barre d'endurence
                _agent.Attributes["Stamina"] = (Convert.ToDouble(_agent.Attributes["Stamina"]) + (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.STAMINA_FACTOR * 4)).ToString();
                _agent.Attributes["EnergyNeeds"] = (Convert.ToDouble(_agent.Attributes["EnergyNeeds"]) + (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.ENERGY_FACTOR)).ToString();
                _agent.Attributes["WaterNeeds"] = (Convert.ToDouble(_agent.Attributes["WaterNeeds"]) + (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.WATER_FACTOR)).ToString();
                _agent.Attributes["Fear"] = (Convert.ToDouble(_agent.Attributes["Fear"]) - (Time.deltaTime * (ActionNames.TimeSpeed / ActionNames.DAY_DURATION) * ActionNames.FEAR_FACTOR * 3000)).ToString();
                if (Convert.ToDouble(_agent.Attributes["Fear"]) < 0)
                {
                    _agent.Attributes["Fear"] = 0.ToString();
                }
                if (Convert.ToDouble(_agent.Attributes["Fear"]) > 100)
                {
                    _agent.Attributes["Fear"] = 1.ToString();
                }


                handleAnimation();

                UnityEngine.Debug.Log(_agent.Attributes["Stamina"]);
            }
            else if (Convert.ToDouble(_agent.Attributes["Stamina"]) >= 1)
            {
                UnityEngine.Debug.Log(_agent.Attributes["Stamina"]);
                _agent.Attributes["Stamina"] = 1.ToString();
                SleepToggler.GetComponent<UnityEngine.UI.Toggle>().isOn = false;

            }

        }

    }
    /// <summary>
    /// Force l'animation de dormir
    /// FAit par Remy XU le 02/04/2023
    /// </summary>
    private void handleAnimation()
    {
        _agent.Animation.ResetTrigger("WalkTrigger");
        _agent.Animation.ResetTrigger("DeadTrigger");
        _agent.Animation.ResetTrigger("AttackTrigger");
        _agent.Animation.ResetTrigger("EatTrigger");
        _agent.Animation.SetTrigger("IdleTrigger");
    }
    /// <summary>
    /// Modifie le nom de l'action quand on passe en mode manuel.
    /// FAit par Remy XU le 07/04/2023-09/04/2023
    /// </summary>
    public void ManualSleepAction()
    {
        if (SleepToggler.GetComponent<UnityEngine.UI.Toggle>().isOn) //si la case dormir est activée
        {
            int i = 0;
            previousAction = _agent._currentAction;
            _agent._currentAction = _agent._currentAction.Parent;


            foreach (ActionTreeNode<AgentAction> action in _agent._currentAction.Children)
            {
                if (i == 0)
                {

                    action.Parent = _agent._currentAction;
                    _agent._currentAction = action;
                    //UnityEngine.Debug.Log(_agent._currentAction.Action.GetType().Name);
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
