using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using TreeEditor;


namespace TMPro.Examples
{
    /// <summary>
    /// Classe pour le bouton boire manuellement
    /// 
    /// Fait par Remy Xu le 29/03/2023
    /// </summary>
    public class DrinkButton : MonoBehaviour
    {
        private Agent _agent;
        private GameObject eauP;
        private GameObject ManualControlToggler;
        [SerializeField] private GameObject Drinker;

        /// <summary>
        /// Variables pour changer et stocker l'action en cours lorsqu'on passe en mode manuel.
        /// </summary>
        public ActionTreeNode<AgentAction> _currentAction;
        public ActionTreeNode<AgentAction> previousAction;
        void Start()
        {
            _agent = null;
            ManualControlToggler = ManualControl.FindChildGameObjectByName(GameObject.Find("Canvas"), "ManualControlToggle");
        }
        /// <summary>
        /// On grise le bouton dans update si on est pas en contrôle manuel.
        /// </summary>
        void Update()
        {
            if (ManualControlToggler.GetComponent<UnityEngine.UI.Toggle>().isOn)
            {
                Drinker.GetComponent<UnityEngine.UI.Button>().interactable = true;
            }
            else
            {
                Drinker.GetComponent<UnityEngine.UI.Button>().interactable = false;
            }
        }
        /// <summary>
        /// Méthode proche de celle de drink() dans DrinkAgentAction.
        /// Cas boire manuellement avec un bouton.
        /// Fait par Remy Xu le 29/03/2023
        /// </summary>
        public void DrinkButtonOnClick()
        {
            _agent = GameObject.Find("AgentManager").GetComponent<AgentStatsGUIUpdater>().AgentToTrack;
            GameObject eauP = null; //Variable permettant de représenter le point d'eau le plus proche.
            double distance; //variable permettant de stocker la distance entre l'agent et un point d'eau.
            double distanceMin = System.Double.PositiveInfinity; ; //variable permettant de stocker la plus petite distance entre l'agent et le point d'eau le plus proche.
            GameObject[] eaux = GameObject.FindGameObjectsWithTag("pointEau"); // On stocke tous les points d'eau du terrain dans un tableau.

            //On recherche le point d'eau le plus proche.
            for (int i = 0; i < eaux.Length; i++)
            {
                distance = Vector3.Distance(_agent.transform.position, eaux[i].transform.position);
                if (distance < distanceMin)
                {
                    eauP = eaux[i];
                    distanceMin = distance;
                }
            }
            if (_agent.GetComponent<UnityEngine.AI.NavMeshAgent>().enabled == false)
            {
                if (Vector3.Distance(eauP.transform.position, _agent.transform.position) <= 100.0f)
                {
                    //ManualDrinkActionEnter();
                    _agent.Attributes["WaterNeeds"] = "0";
                    _agent.Attributes["IsThirsty"] = "false";
                    //ManualDrinkActionExit();
                }
                else
                {
                    UnityEngine.Debug.Log("Vous êtes trop loin de la source d'eau!");
                }
            }
        }
        /// <summary>
        /// Modifie le nom de l'action quand on passe en mode manuel.
        /// (Meme si boire est pour l'instant instantane, à garder si on allonge la duree de boire)
        /// FAit par Remy XU le 07/04/2023
        /// </summary>
        public void ManualDrinkActionEnter()
        {
            int i = 0;
            _agent._currentAction = _agent._currentAction.Parent;
            previousAction = _agent._currentAction;
            UnityEngine.Debug.Log(_agent._currentAction.Children);
            foreach (ActionTreeNode<AgentAction> action in _agent._currentAction.Children)
            {
                if (i == 3)
                {
                    UnityEngine.Debug.Log(_currentAction.Action.GetType().Name);
                    action.Parent = _agent._currentAction;
                    _agent._currentAction = action;
                    UnityEngine.Debug.Log(_currentAction.Action.GetType().Name);
                    //UnityEngine.Debug.Log("Je cherche de la nourriture");
                }
                i++;
            }
        }
        /// <summary>
        /// Rétablie le nom de l'ancienne action quand on passe en mode manuel
        /// FAit par Remy XU le 07/04/2023
        /// </summary>
        public void ManualDrinkActionExit()
        {
            _agent._currentAction = previousAction;
        }
    }
}
