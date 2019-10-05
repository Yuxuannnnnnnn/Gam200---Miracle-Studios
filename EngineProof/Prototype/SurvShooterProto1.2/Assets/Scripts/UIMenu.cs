using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class UIMenu : MonoBehaviour
{
    public GameObject PauseMenu;
    public GameObject OptionsMenu;
    public GameObject QuitMenu;

    public GameObject ListOfButtons;

    bool isPaused = false;
    bool isPauseMenu = false;

    public bool Paused
    {
        get { return isPaused; }
        set { isPaused = value; }
    }

    // Start is called before the first frame update
    void Start()
    {
        PauseMenu.SetActive(false);
        OptionsMenu.SetActive(false);
        QuitMenu.SetActive(false);
        Time.timeScale = 1.0f;
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape) && 
            SceneManager.GetActiveScene().name == "TestLevel")
        {
            Paused = !Paused;            
        }
        Pause(Paused);
    }

    public void ToMain()
    {
        SceneManager.LoadScene("MainMenu");
    }

    public void ToOptions()
    {
        if (SceneManager.GetActiveScene().name == "TestLevel")
        {
            PauseMenu.SetActive(false);            
        }
        else
        {
            ListOfButtons.SetActive(false);
        }
        OptionsMenu.SetActive(true);
    }

    public void Restart()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }

    public void Quit()
    {
        string currScene = SceneManager.GetActiveScene().name;

        if (currScene == "TestLevel")
        {
            SceneManager.LoadScene("MainMenu");
        }
        else
        {
#if UNITY_EDITOR
            UnityEditor.EditorApplication.isPlaying = false;
#else
            Application.Quit();
#endif
        }
    }

    public void Resume()
    {
        Paused = false;
        isPauseMenu = false;
    }

    public void Pause(bool isItPaused)
    {
        if (isPaused && SceneManager.GetActiveScene().name == "TestLevel")
        {
            if (!isPauseMenu)
            {
                PauseMenu.SetActive(true);
                isPauseMenu = true;
            }
            Time.timeScale = 0.0f;
        }
        else if (SceneManager.GetActiveScene().name == "TestLevel")
        {
            UnPause();
        }
    }

    public void UnPause()
    {
        PauseMenu.SetActive(false);
        OptionsMenu.SetActive(false);
        QuitMenu.SetActive(false);
        isPauseMenu = false;
        Time.timeScale = 1.0f;
    }

    public void Back()
    {
        if (SceneManager.GetActiveScene().name == "TestLevel")
        {
            if (OptionsMenu.activeSelf)
            {
                OptionsMenu.SetActive(false);                
            }
            else if (QuitMenu.activeSelf)
            {
                QuitMenu.SetActive(false);                
            }
            PauseMenu.SetActive(true);
        }
        else
        {
            ListOfButtons.SetActive(false);
            OptionsMenu.SetActive(false);
            QuitMenu.SetActive(false);
            ListOfButtons.SetActive(true);
        }
    }

    public void LoadGame()
    {
        SceneManager.LoadScene("TestLevel");
    }

    public void LoadQuit()
    {
        string currScene = SceneManager.GetActiveScene().name;

        if (currScene == "TestLevel")
        {
            PauseMenu.SetActive(false);
        }
        else
        {
            ListOfButtons.SetActive(false);
        }
        QuitMenu.SetActive(true);
    }
}