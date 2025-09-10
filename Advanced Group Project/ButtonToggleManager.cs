using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Classe dédiée à la gestion des boutons et des toggles du contrôle manuel.
/// Pour plus de lisibilité des autres scripts.
/// 
/// Fait par Remy XU le 13/04/2023
/// </summary>


public class ButtonToggleManager : MonoBehaviour
{
    /// <summary>
    /// Variable pour désactiver le contrôle manuel lorsque l'on dort manuellement
    /// + Pour Désactiver les actions lorsque l'on désactive le contrôle manuel
    /// 12/04/2023
    /// </summary>
    [SerializeField] private GameObject SleepToggler;
    [SerializeField] private GameObject EatToggler;
    [SerializeField] private GameObject DrinkButton;
    [SerializeField] private GameObject TogglerAgent;

    private Agent trackedAgent; //variable contenant l'agent traqué lorsqu'on clique dessus.

    // Start is called before the first frame update
    void Start()
    {
        TogglerAgent = ManualControl.FindChildGameObjectByName(GameObject.Find("Canvas"), "ManualControlToggle");
        SleepToggler = ManualControl.FindChildGameObjectByName(GameObject.Find("Canvas"), "SleepToggle");
        EatToggler = ManualControl.FindChildGameObjectByName(GameObject.Find("Canvas"), "EatToggle");
        DrinkButton = ManualControl.FindChildGameObjectByName(GameObject.Find("Canvas"), "DrinkButton");
    }

    // Update is called once per frame
    void Update()
    {
        ButtonAndToggleManager();
    }
    public void ButtonAndToggleManager()
    {
        trackedAgent = GameObject.Find("AgentManager").GetComponent<AgentStatsGUIUpdater>().AgentToTrack;
        if (trackedAgent != null )
        {
            if (trackedAgent.Attributes["IsAlive"] == "true")
            {
                TogglerAgent.GetComponent<UnityEngine.UI.Toggle>().interactable = true;

                if (TogglerAgent.GetComponent<UnityEngine.UI.Toggle>().isOn)
                {
                    DrinkButton.GetComponent<UnityEngine.UI.Button>().interactable = true;
                    SleepToggler.GetComponent<UnityEngine.UI.Toggle>().interactable = true;
                    EatToggler.GetComponent<UnityEngine.UI.Toggle>().interactable = true;
                    if (EatToggler.GetComponent<UnityEngine.UI.Toggle>().isOn == true)
                    {
                        //L'agent ne pourra pas dormir pendant qu'il est en chasse manuelle
                        SleepToggler.GetComponent<UnityEngine.UI.Toggle>().interactable = false;
                    }
                    else
                    {
                        SleepToggler.GetComponent<UnityEngine.UI.Toggle>().interactable = true;
                    }
                    if (SleepToggler.GetComponent<UnityEngine.UI.Toggle>().isOn == true)
                    {
                        //L'agent ne pourra pas manger ni boire pendant qu'il est en train de dormir
                        EatToggler.GetComponent<UnityEngine.UI.Toggle>().interactable = false;
                        DrinkButton.GetComponent<UnityEngine.UI.Button>().interactable = false;
                    }
                    else
                    {
                        DrinkButton.GetComponent<UnityEngine.UI.Button>().interactable = true;
                        EatToggler.GetComponent<UnityEngine.UI.Toggle>().interactable = true;
                    }
                    if (trackedAgent.getIsSwimming() == true)
                    {
                        TogglerAgent.GetComponent<UnityEngine.UI.Toggle>().interactable = false;
                    }
                    else
                    {
                        TogglerAgent.GetComponent<UnityEngine.UI.Toggle>().interactable = true;
                    }
                }
                else
                {
                    //Empeche et désactive toutes les actions manuelles si l'action manuelle est desactivée
                    //fait le 13/04/2023
                    TogglerAgent.GetComponent<UnityEngine.UI.Toggle>().interactable = true;
                    DrinkButton.GetComponent<UnityEngine.UI.Button>().interactable = false;
                    SleepToggler.GetComponent<UnityEngine.UI.Toggle>().interactable = false;
                    EatToggler.GetComponent<UnityEngine.UI.Toggle>().interactable = false;
                    EatToggler.GetComponent<UnityEngine.UI.Toggle>().isOn = false;
                    SleepToggler.GetComponent<UnityEngine.UI.Toggle>().isOn = false;
                }

            }
            //Empeche et désactive tous les boutons lorsque l'agent meurt.
            //fait le 13/04/2023
            else if (trackedAgent.Attributes["IsAlive"] == "false" || trackedAgent.Attributes["SpeciesName"].Equals("Grass"))
            {
                TogglerAgent.GetComponent<UnityEngine.UI.Toggle>().isOn = false;
                SleepToggler.GetComponent<UnityEngine.UI.Toggle>().isOn = false;
                EatToggler.GetComponent<UnityEngine.UI.Toggle>().isOn = false;
                TogglerAgent.GetComponent<UnityEngine.UI.Toggle>().interactable = false;
                DrinkButton.GetComponent<UnityEngine.UI.Button>().interactable = false;
                SleepToggler.GetComponent<UnityEngine.UI.Toggle>().interactable = false;
                EatToggler.GetComponent<UnityEngine.UI.Toggle>().interactable = false;
            }
        }
    }
}
