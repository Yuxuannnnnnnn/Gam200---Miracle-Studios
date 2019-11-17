using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GameControllerBehavior : MonoBehaviour
{
    int enemycount;
    public Player p;
    SoundController sound;

    public Text ecountText;
    public GameObject rocketPowUp;
    public GameObject spawner;

    public int EnemyCount
    {
        get { return enemycount; }
        set { enemycount = value; }
    }

    // Start is called before the first frame update
    void Start()
    {
        //p = GameObject.FindGameObjectWithTag("Player").GetComponent<Player>();
        sound = GameObject.Find("SoundController").GetComponent<SoundController>();

        Time.timeScale = 1.0f;

        sound.PlayBGM(sound.BGMList[0]);
        sound.AdjustBGM(0.3f);
    }

    // Update is called once per frame
    void Update()
    {
        ecountText.text = "Enemy Count: " + EnemyCount;

        if (EnemyCount <= 0)
        {
            SceneManager.LoadScene("Win");
        }

        if (!p)
        {
            SceneManager.LoadScene("Loss");
        }

        Vector3 rand = new Vector3(Random.Range(-8f, 8f), Random.Range(-5f, 5f), 0);

        if (Input.GetKeyDown(KeyCode.J))
        {
            Instantiate(spawner, rand,Quaternion.identity);
        }
        else if (Input.GetKeyDown(KeyCode.K))
        {
            p.Health += 10;
        }
        else if (Input.GetKeyDown(KeyCode.L))
        {
            Instantiate(rocketPowUp, Vector3.zero, Quaternion.identity);
        }
    }
}
