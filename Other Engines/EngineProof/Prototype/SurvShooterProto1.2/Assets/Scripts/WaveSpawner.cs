using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class WaveSpawner : MonoBehaviour
{
    public GameObject Spawner;
    float spawntime;
    UIMenu ui;

    public Text WaveText;
    float waveTexttime;
    float wavevistime;

    int waves = 1;

    Vector3 rand = Vector3.zero;

    // Start is called before the first frame update
    void Start()
    {
        ui = GameObject.FindGameObjectWithTag("GameController").GetComponent<UIMenu>();
        WaveText.text = "Wave 1";
        StartCoroutine("WaveVis");
    }

    // Update is called once per frame
    void Update()
    {        
        if (!ui.Paused)
        {
            spawntime += Time.deltaTime;
            waveTexttime += Time.deltaTime;
            rand = new Vector3(Random.Range(-8f, 8f), Random.Range(-5f, 5f), 0);
        }

        if (spawntime >= 10.0f)
        {
            Instantiate(Spawner, rand, Quaternion.identity);
            spawntime = 0f;
        }

        if (waveTexttime >= 30f)
        {
            waves++;
            WaveText.text = "Wave " + waves;
            StartCoroutine("WaveVis");
            waveTexttime = 0f;
        }
    }

    IEnumerator WaveVis()
    {
        wavevistime += Time.deltaTime;
        if (wavevistime >= 5f)
        {
            WaveText.text = "";
        }
        yield return new WaitForSeconds(1.0f);
    }
}
