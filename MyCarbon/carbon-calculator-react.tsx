import React, { useState } from 'react'
import { Card, CardContent, CardHeader, CardTitle } from '@/components/ui/card'
import { Tabs, TabsContent, TabsList, TabsTrigger } from '@/components/ui/tabs'
import { Input } from '@/components/ui/input'
import { Label } from '@/components/ui/label'
import { Button } from '@/components/ui/button'
import { RadioGroup, RadioGroupItem } from '@/components/ui/radio-group'
import { Alert, AlertTitle, AlertDescription } from '@/components/ui/alert'
import { Loader2 } from 'lucide-react'

const API_URL = 'http://localhost:3000'

const IndividualCalculator = ({ setResults, loading, setLoading }) => {
  const [formData, setFormData] = useState({
    respiratii: '',
    kmTransport: '',
    isMasina: true
  })

  const calculateIndividual = async () => {
    try {
      setLoading(true)
      const response = await fetch(`${API_URL}/calculate/individual`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(formData)
      })
      const data = await response.json()
      setResults(prev => ({ ...prev, individual: data }))
    } catch (error) {
      console.error('Error:', error)
    } finally {
      setLoading(false)
    }
  }

  return (
    <div className="space-y-4">
      <div>
        <Label>Respirații pe minut</Label>
        <Input 
          type="number" 
          value={formData.respiratii}
          onChange={(e) => setFormData({...formData, respiratii: parseInt(e.target.value)})}
          placeholder="Ex: 16"
        />
      </div>
      <div>
        <Label>Kilometri parcurși zilnic</Label>
        <Input 
          type="number"
          value={formData.kmTransport}
          onChange={(e) => setFormData({...formData, kmTransport: parseFloat(e.target.value)})}
          placeholder="Ex: 20"
        />
      </div>
      <RadioGroup
        value={formData.isMasina ? "masina" : "transport"}
        onValueChange={(value) => setFormData({...formData, isMasina: value === "masina"})}
      >
        <div className="flex items-center space-x-2">
          <RadioGroupItem value="masina" id="masina" />
          <Label htmlFor="masina">Mașină personală</Label>
        </div>
        <div className="flex items-center space-x-2">
          <RadioGroupItem value="transport" id="transport" />
          <Label htmlFor="transport">Transport public</Label>
        </div>
      </RadioGroup>
      <Button onClick={calculateIndividual} disabled={loading}>
        {loading ? <Loader2 className="mr-2 h-4 w-4 animate-spin" /> : null}
        Calculează
      </Button>
    </div>
  )
}

const CasaCalculator = ({ setResults, loading, setLoading }) => {
  const [formData, setFormData] = useState({
    tipLocuinta: 'apartament',
    spatiuUtil: '',
    curentElectric: '',
    gazeNaturale: '',
    apaCalda: '',
    apaRece: ''
  })

  const calculateCasa = async () => {
    try {
      setLoading(true)
      const response = await fetch(`${API_URL}/calculate/casa`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(formData)
      })
      const data = await response.json()
      setResults(prev => ({ ...prev, casa: data }))
    } catch (error) {
      console.error('Error:', error)
    } finally {
      setLoading(false)
    }
  }

  return (
    <div className="space-y-4">
      <RadioGroup
        value={formData.tipLocuinta}
        onValueChange={(value) => setFormData({...formData, tipLocuinta: value})}
      >
        <div className="flex items-center space-x-2">
          <RadioGroupItem value="garsoniera" id="garsoniera" />
          <Label htmlFor="garsoniera">Garsonieră</Label>
        </div>
        <div className="flex items-center space-x-2">
          <RadioGroupItem value="apartament" id="apartament" />
          <Label htmlFor="apartament">Apartament</Label>
        </div>
        <div className="flex items-center space-x-2">
          <RadioGroupItem value="casa" id="casa" />
          <Label htmlFor="casa">Casă</Label>
        </div>
      </RadioGroup>
      <div>
        <Label>Spațiu util (m²)</Label>
        <Input 
          type="number"
          value={formData.spatiuUtil}
          onChange={(e) => setFormData({...formData, spatiuUtil: parseFloat(e.target.value)})}
          placeholder="Ex: 70"
        />
      </div>
      <div>
        <Label>Consum curent electric lunar (kWh)</Label>
        <Input 
          type="number"
          value={formData.curentElectric}
          onChange={(e) => setFormData({...formData, curentElectric: parseFloat(e.target.value)})}
          placeholder="Ex: 150"
        />
      </div>
      <div>
        <Label>Consum gaze naturale lunar (m³)</Label>
        <Input 
          type="number"
          value={formData.gazeNaturale}
          onChange={(e) => setFormData({...formData, gazeNaturale: parseFloat(e.target.value)})}
          placeholder="Ex: 100"
        />
      </div>
      <div>
        <Label>Consum apă caldă lunar (litri)</Label>
        <Input 
          type="number"
          value={formData.apaCalda}
          onChange={(e) => setFormData({...formData, apaCalda: parseFloat(e.target.value)})}
          placeholder="Ex: 2000"
        />
      </div>
      <div>
        <Label>Consum apă rece lunar (litri)</Label>
        <Input 
          type="number"
          value={formData.apaRece}
          onChange={(e) => setFormData({...formData, apaRece: parseFloat(e.target.value)})}
          placeholder="Ex: 3000"
        />
      </div>
      <Button onClick={calculateCasa} disabled={loading}>
        {loading ? <Loader2 className="mr-2 h-4 w-4 animate-spin" /> : null}
        Calculează
      </Button>
    </div>
  )
}

const RegimAlimentarCalculator = ({ setResults, loading, setLoading }) => {
  const [regim, setRegim] = useState('omnivor')

  const calculateRegim = async () => {
    try {
      setLoading(true)
      const response = await fetch(`${API_URL}/calculate/regim`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({ regim })
      })
      const data = await response.json()
      setResults(prev => ({ ...prev, regimAlimentar: data }))
    } catch (error) {
      console.error('Error:', error)
    } finally {
      setLoading(false)
    }
  }

  return (
    <div className="space-y-4">
      <RadioGroup value={regim} onValueChange={setRegim}>
        <div className="flex items-center space-x-2">
          <RadioGroupItem value="vegan" id="vegan" />
          <Label htmlFor="vegan">Vegan</Label>
        </div>
        <div className="flex items-center space-x-2">
          <RadioGroupItem value="vegetarian" id="vegetarian" />
          <Label htmlFor="vegetarian">Vegetarian</Label>
        </div>
        <div className="flex items-center space-x-2">
          <RadioGroupItem value="omnivor" id="omnivor" />
          <Label htmlFor="omnivor">Omnivor</Label>
        </div>
      </RadioGroup>
      <Button onClick={calculateRegim} disabled={loading}>
        {loading ? <Loader2 className="mr-2 h-4 w-4 animate-spin" /> : null}
        Calculează
      </Button>
    </div>
  )
}

const CarbonCalculator = () => {
  const [loading, setLoading] = useState(false)
  const [results, setResults] = useState({
    individual: null,
    casa: null,
    regimAlimentar: null
  })

  return (
    <div className="w-full max-w-4xl mx-auto p-4">
      <Card>
        <CardHeader>
          <CardTitle>Calculator Amprentă de Carbon</CardTitle>
        </CardHeader>
        <CardContent>
          <Tabs defaultValue="individual">
            <TabsList className="grid w-full grid-cols-3">
              <TabsTrigger value="individual">Individual</TabsTrigger>
              <TabsTrigger value="casa">Casă</TabsTrigger>
              <TabsTrigger value="regim">Regim Alimentar</TabsTrigger>
            </TabsList>
            <TabsContent value="individual">
              <IndividualCalculator setResults={setResults} loading={loading} setLoading={setLoading} />
            </TabsContent>
            <TabsContent value="casa">
              <CasaCalculator setResults={setResults} loading={loading} setLoading={setLoading} />
            </TabsContent>
            <TabsContent value="regim">
              <RegimAlimentarCalculator setResults={setResults} loading={loading} setLoading={setLoading} />
            </TabsContent>
          </Tabs>

          {Object.values(results).some(r => r !== null) && (
            <Alert className="mt-4">
              <AlertTitle>Rezultate calcul amprentă de carbon</AlertTitle>
              <AlertDescription>
                <div className="space-y-2">
                  {results.individual && (
                    <div>
                      <p>Individual:</p>
                      <ul className="list-disc pl-5">
                        <li>Respirații: {results.individual.respiratii.toFixed(2)} kg CO2/an</li>
                        <li>Transport: {results.individual.transport.toFixed(2)} kg CO2/an</li>
                        <li>Total: {results.individual.total.toFixed(2)} kg CO2/an</li>
                      </ul>
                    </div>
                  )}
                  {results.casa && (
                    <div>
                      <p>Casa:</p>
                      <ul className="list-disc pl-5">
                        <li>Curent electric: {results.casa.curentElectric.toFixed(2)} kg CO2/an</li>
                        <li>Gaze naturale: {results.casa.gazeNaturale.toFixed(2)} kg CO2/an</li>
                        <li>Apă caldă: {results.casa.apaCalda.toFixed(2)} kg CO2/an</li>
                        <li>Apă rece: {results.casa.apaRece.toFixed(2)} kg CO2/an</li>
                        <li>Total: {results.casa.total.toFixed(2)} kg CO2/an</li>
                      </ul>
                    </div>
                  )}
                  {results.regimAlimentar && (
                    <p>Regim alimentar: {results.regimAlimentar.total.toFixed(2)} kg CO2/an</p>
                  )}
                </div>
              </AlertDescription>
            </Alert>
          )}
        </CardContent>
      </Card>
    </div>
  )
}

export default CarbonCalculator
